#include <vector>
#include <string>

#include <SurfaceMesh/SurfaceMesh.h>
#include <SurfaceMesh/IO.h>
#include <dbg.h>

typedef Surface_Mesh::Scalar Scalar;
typedef Surface_Mesh::Point Point;
typedef Surface_Mesh::SurfaceMesh::Vertex Vertex;

void gen2DPlane(size_t row, size_t col, Scalar step, const std::string& filename) {
    Surface_Mesh::SurfaceMesh mesh;
    std::vector<Point> points;
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            points.emplace_back(i * step, j * step, 0);
        }
    }
    for (const auto &p : points) mesh.add_vertex(p);
    for (int i = 0; i < row - 1; i++) {
        for (int j = 0; j < col - 1; j++) {
            int top_left = i * row + j;
            int top_right = top_left + 1;
            int bottom_left = (i + 1) * row + j;
            int bottom_right = bottom_left + 1;
            mesh.add_triangle(Vertex(top_left), Vertex(top_right), Vertex(bottom_left));
            mesh.add_triangle(Vertex(top_right), Vertex(bottom_right), Vertex(bottom_left));
        }
    }
    dbg(mesh.n_faces());
    Surface_Mesh::write_obj(mesh, filename);

}

int main(int argc, char *argv[]) {
    assert(argc == 5);
    gen2DPlane(std::stoi(argv[1]), std::stoi(argv[2]), std::stof(argv[3]), argv[4]);
    return 0;
}
