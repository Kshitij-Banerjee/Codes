#tester script for prison escap
import codility_PrisonEscape

# 7    9         |8| 
# |    |          |
# 3 -- 2 --|1|-- '0' --|4|
#                 |
#                 5 -- '6' --|10|

def UT1():
	A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
	B = [0, 1, 2, 0, 0, 5, 3, 0, 2, 6]
	C = [ 0, 6 ]
  	ans = codility_PrisonEscape.solution( A, B, C )
	if( ans != 4 ):
		print "Test Case A failed with:", ans
	pass

#       |10|         3    7    9
#        |           |     |    |
#|6| -- '4' -- '1'--|0| -- 2 -- 5 -- 8

def UT2():
	A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
	B = [0, 0, 0, 1, 2, 4, 2, 5, 5, 4] 
	C = [1, 4]

	ans= codility_PrisonEscape.solution( A, B, C )
	if( ans != 3 ):
		print "Test Case V failed with:", ans
	pass
#            |7|
#             |
#     |8|--  '6'    5
#             |    |
# |0|-- '1'--|2| -- 3 -- 4
def UT3():
	A = [0,1,2,3,3,2,6,6]
	B = [1,2,3,4,5,6,8,7]
	C = [1,6]
	ans = codility_PrisonEscape.solution( A, B, C)
	if( ans != 4 ):
		print "Test Case 3 failed with:", ans
	pass
#	        |6|
#	         |
#           3 --'4'--|5|
#           |
#|8|--'1'--|0|-- 2
#           |
#    |10|--'7'--|9| 

def UT4():
	A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]
	B = [0, 0, 0, 3, 4, 4, 0, 1, 7, 7 ]
	C = [1, 4, 7]

	ans = codility_PrisonEscape.solution( A, B, C)
	if( ans != 6 ):
		print "Test Case 4 failed with:", ans
	pass
#             2 -- 4
#8 -- 3-- 1-- 0 -- 5
#            |6|--'7'--|9|
#		 |10|
def UT5():
	A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]
	B = [0, 0, 1, 2, 0, 0, 6, 3, 7, 7]
	C = [7]

	ans = codility_PrisonEscape.solution( A, B, C)
	if( ans != 3 ):
		print "Test Case 5 failed with:", ans
	pass
#                   |8|
#          2 -- 4 --'5'--|7|-- 9
#10 -- 1--|0|--'3'--|6|
def UT6():
	A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]
	B = [0, 0, 0, 2, 4, 3, 5, 5, 7, 1]
	C = [3,5]

	ans = codility_PrisonEscape.solution( A, B, C)
	if( ans != 4 ):
		print "Test Case 5 failed with:", ans
	pass

def main():
	UT1()
	print "============================================"
	UT2()
	print "============================================"
	UT3()
	print "============================================"
	UT4()
	print "============================================"
	UT5()
	print "============================================"
	UT6()
	print "============================================"
	pass

if __name__ == "__main__":
	main()


