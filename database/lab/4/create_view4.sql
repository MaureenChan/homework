
use student
go
create view not_punish_dept
as
	select department.dno, dept_name
		from department
		where department.dno not in (
			select punishment_levels.dno
				from punishment_levels
				where punish_id  in(
					select punish_id
						from punishment
				)
		);
