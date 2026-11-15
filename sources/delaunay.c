#include <stdlib.h>
#include "delaunay.h"

static bool triangle_has_super_vertex(TRIANGLE triangle, int n) {
    return triangle.a >= n || triangle.b >= n || triangle.c >= n;
}

static bool point_in_circumcircle(TSP *tsp, TRIANGLE triangle, int p) {
    Node pa = tsp->nodes[triangle.a];
    Node pb = tsp->nodes[triangle.b];
    Node pc = tsp->nodes[triangle.c];
    Node pp = tsp->nodes[p];

    double ax = pa.x - pp.x;
    double ay = pa.y - pp.y;
    double bx = pb.x - pp.x;
    double by = pb.y - pp.y;
    double cx = pc.x - pp.x;
    double cy = pc.y - pp.y;

    double det = (ax * ax + ay * ay) * (bx * cy - by * cx)
               - (bx * bx + by * by) * (ax * cy - ay * cx)
               + (cx * cx + cy * cy) * (ax * by - ay * bx);

    double orient = (pb.x - pa.x) * (pc.y - pa.y) -
                    (pb.y - pa.y) * (pc.x - pa.x);

    if (orient > 0) return det > 1e-9;
    return det < -1e-9;
}

TRIANGLES *BuildDelaunay(TSP *tsp) {
    int n = tsp->dimension;
    TRIANGLES *triangles = ConstructTriangles();
    triangles->capacity = 0;
    triangles->count = 0;

    AppendSuperTriangle(tsp);

    TRIANGLE t = {.a = n, .b = n+1, .c = n+2};
    AddTriangle(triangles, t);

    for (int p = 0; p < n; p++) {
        POLYGON polygon;
        polygon.count = 0;
        polygon.capacity = 0;
        polygon.edges = NULL;

        TRIANGLES *kept = ConstructTriangles();
        kept->count = 0;
        kept->capacity = 0;

        for (int i = 0; i < triangles->count; i++) {
            TRIANGLE triangle = triangles->triangles[i];
            EDGE e1 = {triangle.a, triangle.b};
            EDGE e2 = {triangle.b, triangle.c};
            EDGE e3 = {triangle.c, triangle.a};

            if (point_in_circumcircle(tsp, triangle, p)) {
                AddEdge(&polygon, &e1);
                AddEdge(&polygon, &e2);
                AddEdge(&polygon, &e3);
            } else {
                AddTriangle(kept, triangle);
            }
        }

        int boundary_count = 0;
        unique_boundary_edges(&polygon, &boundary_count);

        DeconstructTriangles(triangles);
        triangles = kept; 

        for (int i = 0; i < boundary_count; i++) {
            TRIANGLE t = {.a = polygon.edges[i].a, .b = polygon.edges[i].b, .c = p};
            AddTriangle(triangles, t);
        }

        free(polygon.edges);
    }

    TRIANGLES *final = ConstructTriangles();
    int final_count = 0;
    int final_capacity = 0;

    for (int i = 0; i < triangles->count; i++) {
        TRIANGLE triangle = triangles->triangles[i];
        if (!triangle_has_super_vertex(triangle, n)) {
            TRIANGLE t = {.a = triangle.a, .b = triangle.b, .c = triangle.c };
            AddTriangle(final, t);
        }
    }

    DeconstructTriangles(triangles);
    RemoveSuperTriangle(tsp);
    
    return final;
}

