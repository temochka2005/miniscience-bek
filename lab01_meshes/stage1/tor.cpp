#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("tor3");

  double lc = 1e-2;
  // для аргументов в gmsh::model::occ::cut
  gmsh::vectorpair outDimTags;
  std::vector<gmsh::vectorpair> outDimTagsMap;

  // объекты
  gmsh::model::occ::addTorus(0, 0, 0, 4*lc, lc, 1); // внешний тор
  gmsh::model::occ::addTorus(0, 0, 0, 4*lc, 0.5 * lc, 2); // внутренний
  gmsh::model::occ::cut({{3, 1}}, {{3, 2}}, outDimTags, outDimTagsMap, 3); // вырезаем внутренний из внешнего



  gmsh::model::occ::synchronize();

  gmsh::option::setNumber("Mesh.MeshSizeFactor", 0.3);
  gmsh::model::mesh::generate(3);


  gmsh::write("tor.msh");


  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}

