#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("t2");

  double lc = 1e-2;
  // A - 1
  gmsh::model::geo::addPoint(0, 0, 0, lc, 1);
  // B - 2
  gmsh::model::geo::addPoint(.1, 0, 0, lc, 2);
  // C - 3
  gmsh::model::geo::addPoint(.1, .1, 0, lc, 3);
  // D - 4
  gmsh::model::geo::addPoint(0, .1, 0, lc, 4);

  // A1 - 5
  gmsh::model::geo::addPoint(0, 0, .1, lc, 5);
  // B1 - 6
  gmsh::model::geo::addPoint(.1, 0, .1, lc, 6);
  // C1 - 7
  gmsh::model::geo::addPoint(.1, .1, .1, lc, 7);
  // D1 - 8
  gmsh::model::geo::addPoint(.0, .1, .1, lc, 8);


  // A->B->C->D
  gmsh::model::geo::addLine(1, 2, 12); // A B
  gmsh::model::geo::addLine(2, 3, 23); // B C
  gmsh::model::geo::addLine(3, 4, 34); // C D
  gmsh::model::geo::addLine(4, 1, 41); // D A


  // A->A1->B1->B
  gmsh::model::geo::addLine(1, 5, 15); // A A1
  gmsh::model::geo::addLine(5, 6, 56); // A1 B1
  gmsh::model::geo::addLine(6, 2, 62); // B1 B
  // для B A не забыть минус у этой(тег 12) линии gmsh::model::geo::addLine(1, 2, 12); 
  

  // B->C->C1->B1
   // уже задана gmsh::model::geo::addLine(2, 3, 23); B C
  gmsh::model::geo::addLine(3, 7, 37); // C C1
  gmsh::model::geo::addLine(7, 6, 76); // C1 B1
  // B1 B уже задана gmsh::model::geo::addLine(6, 2, 62); B1 B


  // C->C1->D1->D
  // C C1 уже задана gmsh::model::geo::addLine(3 7, 37); // C C1
  gmsh::model::geo::addLine(7, 8, 78); // C1 D1 
  gmsh::model::geo::addLine(8, 4, 84); // D1 D
  // для D C не забыть минус у этой(тег 34) линии gmsh::model::geo::addLine(3, 4, 34); // D C


  // A1->B1->C1->D1
  // A1 B1 уже задана gmsh::model::geo::addLine(5, 6, 56); // A1 B1 
  // для B1 C1 не забыть минус у этой(тег 76) линии gmsh::model::geo::addLine(7, 6, 76);// B1 C1
  // C1 D1 уже задана gmsh::model::geo::addLine(7, 8, 78); // C1 D1 
  gmsh::model::geo::addLine(8, 5, 85); // D1 A1


  // A->A1->D1->D
  // A A1 уже задана gmsh::model::geo::addLine(1, 5, 15); A A1
  gmsh::model::geo::addLine(5, 8, 58); // A1 D1
  // D1 D уже задана gmsh::model::geo::addLine(8, 4, 84); // D1 D
  // D A уже задана gmsh::model::geo::addLine(4, 1, 41); // D A

  

  // ABCD
  gmsh::model::geo::addCurveLoop({12, 23, 34, 41}, 1234);
  gmsh::model::geo::addPlaneSurface({1234}, 1234);

  // AA1B1B
  gmsh::model::geo::addCurveLoop({15, 56, 62, -12}, 1562);
  gmsh::model::geo::addPlaneSurface({1562}, 1562);

  // BCC1B1
  gmsh::model::geo::addCurveLoop({23, 37, 76, 62}, 2376);
  gmsh::model::geo::addPlaneSurface({2376}, 2376);


  // CC1D1D
  gmsh::model::geo::addCurveLoop({37, 78, 84, -34}, 3784);
  gmsh::model::geo::addPlaneSurface({3784}, 3784);

  // A1B1C1D1
  gmsh::model::geo::addCurveLoop({56, -76, 78, 85}, 5678);
  gmsh::model::geo::addPlaneSurface({5678}, 5678);


  // AA1D1D
  gmsh::model::geo::addCurveLoop({15, -85, 84, 41}, 1584);
  gmsh::model::geo::addPlaneSurface({1584}, 1584);


  gmsh::model::geo::addSurfaceLoop({1234, 1562, 2376, 3784, 5678, 1584}, 1);
  gmsh::model::geo::addVolume({1});

  gmsh::model::geo::synchronize();

  gmsh::model::mesh::generate(3);

  gmsh::write("t2.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}

