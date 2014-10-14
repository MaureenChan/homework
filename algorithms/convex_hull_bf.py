#brute force convex_hull
import random

def getline(p1, p2):
	a = p2['y'] - p1['y']	#a = y2 - y1
	b = p1['x'] - p2['x']	#b = x1 - x2
	c = p1['x'] * p2['y'] - p1['y'] * p2['x']	#c = x1 * y2 - y1 * x2
	return {'a' : a, 'b' : b, 'c' : c};

#get true line
def judge(points,line):
	n = len(points)
	values = []
	for i in range(n):
		#val = a * x + b * y - c	
		val = points[i]['x'] * line['a'] + points[i]['y'] * line['b'] - line['c']
		values.append(val)

	#select the standard side
	for i in range(n):
		if (values[i] < 0):
			flag = -1
			break
		elif (values[i] > 0):
			flag = 1
			break
		elif (values[i] == 0):
			flag = 0
		else:
			return -1;

	#judge the side
	for i in range(n):
		if ((values[i] > 0 and flag < 0) or (values[i] < 0 and flag > 0)):	
			return -1;
		
	values[:] = []
	return 1;

def convex_hull(points):
	n = len(points)
	true_points = []  #store true line
	for i in range(n-1):
		for j in range(i+1, n):
			#get one line test all points
			line = getline(points[i],points[j])  
			if (judge(points,line) == 1):
				true_points.append([points[i],points[j]])

	print true_points

def main():
	n = input("Please input point number:")
	points = [];
	#create points kept in points[] 
	for i in range(n):
		a = random.randint(0,5)
		b = random.randint(0,5)
		point = {'x':a,'y':b}
		points.append(point)
	
	#call convex_hull
	convex_hull(points)
	
	print points
	print '\n'
	print '\n'
	

	
if __name__ == '__main__':
	main()


