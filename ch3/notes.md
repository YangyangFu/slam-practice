# Chapter 3: 3-D Rigid Body Dynamic 

## Goals:
- understand how to describe the movement dynamics of a rigid body in 3-D space
- understand key C++ library for matrix and geometry operations: `Eigen`, etc.

## 3.1 Matrix Rotation

### 3.1.1 Vector and Coordination

**Inner Product**
Define two vectors:

$\textbf{a} = [a_1, a_2, ... a_n]$

$\textbf{b} = [b_1, b_2, ..., b_n]$

Inner product (dot product) `->` scalor: $\textbf{a} \cdot \textbf{b}= \textbf{a}^T\textbf{b} = \sum a_ib_i$ 

Outer product (tensor product) `->` vector:  $\textbf{a} \otimes \textbf{b}$

Outer product seems a very important topic:
- tutorial: https://kconrad.math.uconn.edu/blurbs/linmultialg/tensorprod.pdf

### 3.1.2 Coordination Transformation

Usually in robotics, there are two coordiations. One is a global coordination,