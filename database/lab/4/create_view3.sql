use student
go
create view not_reward_dept
as
	select department.dno, dept_name
		from department
		where department.dno not in (
			select reward_levels.dno
				from reward_levels
				where reward_id  in(
					select reward_id
						from reward
				)
		);
