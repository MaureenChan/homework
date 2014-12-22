use SC
go 
create procedure StuInfo
@class_no char(4)
as
	select s_no, sex, sname, sbirthday
		from student
		where class_no = @class_no;
