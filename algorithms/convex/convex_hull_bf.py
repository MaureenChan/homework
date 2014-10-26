#brute force convex_hull
import random
from graphics import *

win = GraphWin('Convex_hull', 800, 800)

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
	for i in range(n-1):
		for j in range(i+1, n):
			#get one line test all points
			line = getline(points[i],points[j])  
			if (judge(points,line) == 1):
				ln = Line(Point(points[i]['x'],points[i]['y']), Point(points[j]['x'], points[j]['y']))
				ln.draw(win)
	raw_input();	


def main():
	#draw Entry
	instructions = Text(Point(win.getWidth()/2,40),"Please input point number:\nThen click the mouse")
	instructions.draw(win)
	entry1 = Entry(Point(win.getWidth()/2, 70), 10)
	entry1.draw(win)

	#get point number
	win.getMouse()
	entry = entry1.getText()
	n = int(entry)

	#create points kept in points[] 
	points = []
	for i in range(n):
		a = random.randint(100,700)
		b = random.randint(100,700)
		pt = Point(a,b)
		pt.draw(win)
		point = {'x':a,'y':b}
		points.append(point)
	
	#call convex_hull
	convex_hull(points)
	

	
if __name__ == '__main__':
	main()


