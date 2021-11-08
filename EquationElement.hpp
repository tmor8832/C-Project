//
//  EquationElement.hpp
//  Solver(1)
//
//  Created by Mac on 15/03/2017.
//  Copyright © 2017 Thomas Morris. All rights reserved.
//

#ifndef EquationElement_hpp
#define EquationElement_hpp
#include <iostream>
#include "EquationSolver.hpp"

class EquationElement : public EquationSolver {
protected:
           double y[21], x[21];

public:
    EquationElement();
    void PolynomialElements();
    void TanElements();
    void SinElements();
    void CosElements();
    void CheckWithinRange();
    void OutputElements();
};

#endif /* EquationElement_hpp */
