#include <iostream>

#include "strategy_solver_binsearch2.h"
#include "util.h"

// #define DEBUG_FORMULA

bool strategy_solver_binsearch2t::iterate(invariantt &_inv)
{
  tpolyhedra_domaint::templ_valuet &inv = 
    static_cast<tpolyhedra_domaint::templ_valuet &>(_inv);

  bool improved = false;

  literalt activation_literal0 = new_context(); //for improvement check

  exprt inv_expr = tpolyhedra_domain.to_pre_constraints(inv);

  solver << or_exprt(inv_expr, literal_exprt(activation_literal0));

  exprt::operandst strategy_cond_exprs;
  tpolyhedra_domain.make_not_post_constraints(inv, 
    strategy_cond_exprs, strategy_value_exprs); 
  
  strategy_cond_literals.resize(strategy_cond_exprs.size());
  
  for(unsigned i = 0; i<strategy_cond_exprs.size(); i++)
  {  
    strategy_cond_literals[i] = solver.convert(strategy_cond_exprs[i]);
    strategy_cond_exprs[i] = literal_exprt(strategy_cond_literals[i]);
  }
  debug() << eom;

  solver << or_exprt(disjunction(strategy_cond_exprs),
		     literal_exprt(activation_literal0));

#if 0
  debug() << "solve(): ";
#endif

  std::map<tpolyhedra_domaint::rowt,symbol_exprt> symb_values;
  std::map<tpolyhedra_domaint::rowt,constant_exprt> lower_values;
  exprt::operandst blocking_constraint;

  std::set<tpolyhedra_domaint::rowt> improve_rows;
  while(solve() == decision_proceduret::D_SATISFIABLE) //improvement check
  { 
#if 0
    debug() << "SAT" << eom;
#endif
    improved = true;

    unsigned row=0;  
    for(;row<strategy_cond_literals.size(); row++)
    {
      if(solver.l_get(strategy_cond_literals[row]).is_true()) 
      {
#if 0
        debug() << "improve row " << row  << eom;
#endif
        improve_rows.insert(row);
	symb_values[row] = tpolyhedra_domain.get_row_symb_value(row);
	lower_values[row] =
		       simplify_const(solver.get(strategy_value_exprs[row]));
	blocking_constraint.push_back(
          literal_exprt(!strategy_cond_literals[row]));
      }
    }
    solver << or_exprt(conjunction(blocking_constraint),
		     literal_exprt(activation_literal0));
  }
  pop_context(); //improvement check

  if(!improved) //done
  {
#if 0
    debug() << "UNSAT" << eom;
#endif
    return improved;
  }

  //symbolic value system
  literalt activation_literal1 = new_context(); //symbolic value system
  exprt pre_inv_expr = 
    tpolyhedra_domain.to_symb_pre_constraints(inv,improve_rows);
  solver << or_exprt(pre_inv_expr, literal_exprt(activation_literal1));
  exprt post_inv_expr = 
    tpolyhedra_domain.to_symb_post_constraints(improve_rows);
  solver << or_exprt(post_inv_expr, literal_exprt(activation_literal1));

  assert(lower_values.size()>=1);
  std::map<tpolyhedra_domaint::rowt,symbol_exprt>::iterator 
    it = symb_values.begin();
  exprt _lower = lower_values[it->first];
#if 0
  debug() << "update row " << it->first << ": " 
	    << from_expr(ns,"",lower_values[it->first]) << eom;
#endif
  tpolyhedra_domain.set_row_value(it->first,lower_values[it->first],inv);
  exprt _upper = 
    tpolyhedra_domain.get_max_row_value(it->first);
  exprt sum = it->second;
  for(it++; it != symb_values.end(); it++)
  {
    sum = plus_exprt(sum,it->second);
    _upper = plus_exprt(_upper,tpolyhedra_domain.get_max_row_value(it->first));
    _lower = plus_exprt(_lower,lower_values[it->first]);

#if 0
	    debug() << "update row " << it->first << ": " 
		    << from_expr(ns,"",lower_values[it->first]) << eom;
#endif
    tpolyhedra_domain.set_row_value(it->first,lower_values[it->first],inv);
  }
  extend_expr_types(sum);
  extend_expr_types(_upper);
  extend_expr_types(_lower);
  tpolyhedra_domaint::row_valuet upper = simplify_const(_upper);
  tpolyhedra_domaint::row_valuet lower = simplify_const(_lower);

  while(tpolyhedra_domain.less_than(lower,upper))   
    {
      tpolyhedra_domaint::row_valuet middle = 
	tpolyhedra_domain.between(lower,upper);
      if(!tpolyhedra_domain.less_than(lower,middle)) middle = upper;

      // row_symb_value >= middle
      exprt c = binary_relation_exprt(sum,ID_ge,middle);

#if 0
      debug() << "upper: " << from_expr(ns,"",upper) << eom;
      debug() << "middle: " << from_expr(ns,"",middle) << eom;
      debug() << "lower: " << from_expr(ns,"",lower) << eom;
#endif

      literalt activation_literal2 = new_context(); // binary search iteration

#if 0
      debug() << "constraint: " << from_expr(ns, "", c) << eom;
#endif

      solver << or_exprt(c,literal_exprt(activation_literal2)); 

      if(solve() == decision_proceduret::D_SATISFIABLE) 
	{ 
#if 0
	  debug() << "SAT" << eom;
#endif
     
	  lower = middle;

	  for(std::map<tpolyhedra_domaint::rowt,symbol_exprt>::iterator 
		it = symb_values.begin(); it != symb_values.end(); it++)
	  { 
	    constant_exprt lower = simplify_const(solver.get(it->second));
#if 0
	    debug() << "update row " << it->first << ": " 
		    << from_expr(ns,"",lower) << eom;
#endif
	    tpolyhedra_domain.set_row_value(it->first,lower,inv);
	  }
	}
      else 
	{
#if 0
	  debug() << "UNSAT" << eom;
#endif

	  if(!tpolyhedra_domain.less_than(middle,upper)) middle = lower;

	  upper = middle;
	}
      pop_context(); // binary search iteration
    }   

  pop_context();  //symbolic value system


  return improved;
}
