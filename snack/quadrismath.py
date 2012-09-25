from game import *

class mat2:
	def __init__(self, mat1, mat2=None):
		if mat2 is None:
			self.mat = array(mat1, dtype=float)
		else:
			self.mat = array([mat1,mat2], dtype=float)
	def __mul__(self, other):
		return mat2(dot(self.mat, other.mat))
	def inv(self):
		return mat2(inv(self.mat))
	