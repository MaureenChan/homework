select s_no, sname, sex, sbirthday 
	from student;

select s_no, sname, '2014' - sbirthday age 
	from student;

select s_no, sname, sex, sbirthday 
	from student
	where dno = '1';

select s_no, sname, sex, sbirthday
	from student
	where spno = '105' 
		and class_no = '005';

select s_no, sname, sex, sbirthday
	from student
	where dno = '1' 
		and sbirthday > '1988-01-10';

select s_no, sname, sex, sbirthday 
	from student
	order by sbirthday ASC;

select s_no, sname, sex, sbirthday, dept_name, spname
	from student, department, speciality
	where student.dno = department.dno 
		and student.spno = speciality.spno;

select student.s_no, sname, spname, score
	from student, student_course, speciality
	where student_course.tcid = '2222' 
		and student_course.s_no = student.s_no 
		and student.spno = speciality.spno;

select student.s_no, sname, cname
	from student_course, student, teacher_course, course
	where student_course.score < 60 
		and student_course.tcid = teacher_course.tcid 
		and student.s_no = student_course.s_no 
		and teacher_course.cno = course.cno;

select s_no, sname
	from student
	where spno in(
		select spno 
			from course
			where cno != '123456'
		);
		
select s_no, sname
	from student
	where 60 < ALL (
		select score
			from student_course
			where student.s_no = student_course.s_no
	);
