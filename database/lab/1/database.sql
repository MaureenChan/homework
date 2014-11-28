create database SC on (
	name = student_database_info,
	filename = 'C:\database\student.mdf',
	size = 30mb,
	filegrowth = 20%
)
log on(
	name = student_log_file,
	filename = 'C:\database\r_stdent.ldf',
	size = 3mb,
	filegrowth = 1mb
)
