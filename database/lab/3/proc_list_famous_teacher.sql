use SC
go 
create procedure list_famous_teachers
as
	select t_no, t_name, t_sex, year(getdate())-Year(t_birthday) age
		from teacher
		where year(getdate())-Year(t_birthday) < '35';
