#include "foo/Foo.hpp"

#include <ortools/glop/lp_solver.h>
#include <ortools/lp_data/lp_data.h>
#include <ortools/lp_data/lp_types.h>

#include <iostream>

namespace foo {
using operations_research::glop::ColIndex;
using operations_research::glop::DenseRow;
using operations_research::glop::GlopParameters;
using operations_research::glop::LinearProgram;
using operations_research::glop::LPSolver;
using operations_research::glop::ProblemStatus;
using operations_research::glop::RowIndex;

void helloWorld() {
  std::cout << "foo::hello()";

  LinearProgram lp;
  // Create the variables x and y.
  ColIndex col_x = lp.FindOrCreateVariable("x");
  lp.SetVariableBounds(col_x, 0.0, 1.0);
  ColIndex col_y = lp.FindOrCreateVariable("y");
  lp.SetVariableBounds(col_y, 0.0, 2.0);

  // Create linear constraint: 0 <= x + y <= 2.
  RowIndex row_r1 = lp.FindOrCreateConstraint("r1");
  lp.SetConstraintBounds(row_r1, 0.0, 2.0);
  lp.SetCoefficient(row_r1, col_x, 1);
  lp.SetCoefficient(row_r1, col_y, 1);

  // Create objective function: 3 * x + y.
  lp.SetObjectiveCoefficient(col_x, 3);
  lp.SetObjectiveCoefficient(col_y, 1);
  lp.SetMaximizationProblem(true);

  lp.CleanUp();

  std::cout << "Number of variables = " << lp.num_variables() << std::endl;
  std::cout << "Number of constraints = " << lp.num_constraints() << std::endl;

  LPSolver solver;
  GlopParameters parameters;
  parameters.set_provide_strong_optimal_guarantee(true);
  solver.SetParameters(parameters);

  ProblemStatus status = solver.Solve(lp);
  if (status == ProblemStatus::OPTIMAL) {
    std::cout << "Optimal solution found !" << std::endl;
    // The objective value of the solution.
    std::cout << "Optimal objective value = " << solver.GetObjectiveValue()
              << std::endl;
    // The value of each variable in the solution.
    const DenseRow& values = solver.variable_values();
    std::cout << "Solution:" << std::endl
              << "x = " << values[col_x] << std::endl
              << ", y = " << values[col_y] << std::endl;
  }
}

void Foo::operator()() const { std::cout << "foo::Foo()()"; }
}  // namespace foo
