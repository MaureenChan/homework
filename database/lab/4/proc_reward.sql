use student
go
create procedure proc_reward
@s_no char(8)
as
	select count(record_re_id)
		from reward
		where s_no = @s_no;
