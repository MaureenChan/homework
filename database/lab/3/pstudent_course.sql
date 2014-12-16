use SC
go
create procedure proc_student_course 
@class_no char(4),
@spno char(8),
@dno char(6),
@tcid smallint
as
	insert into student_course(s_no, tcid)
		select student.s_no, @tcid
			from student_course, student
			where class_no = @class_no
			and spno = @spno
			and dno = @dno
			and student.s_no not in(
				select s_no
					from student_course
					where tcid = @tcid
	);
