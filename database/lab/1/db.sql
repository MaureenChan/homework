create database SC;
use SC;

create table department (
	dno char(6),
	dept_name char(20) not null,
	header char(8),
	primary key(dno)
);

create table speciality (
	spno char(8),
	dno char(6)  not null,
	spname char(20) not null,
	foreign key (dno) references department(dno),
	primary key(spno)
);

create table class (
	spno char(8),
	class_no char(4),
	header char(8),
	foreign key(spno) references speciality(spno),
	primary key(class_no, spno)
);

create table student (
	s_no char(8),
	sname char(8) not null,
	sex char(2),
	sbirthday datetime,
	dno char(6) ,
	spno char(8),
	class_no char(4),
	foreign key(dno) references department(dno),
	foreign key(spno) references speciality(spno),
	primary key(s_no)
);

create table teacher (
	t_no char(8),
	t_name char(8) not null,
	t_sex char(2),
	t_birthday datetime,
	dno char(6),
	tech_title char(10),
	foreign key(dno) references department(dno),
	primary key(t_no)
);

create table student_course (
	s_no char(8),
	tcid smallint,
	score tinyint,
	foreign key (s_no) references student(s_no)
		on delete cascade,
	primary key(s_no, tcid)
);

create table course (
	cno char(10),
	cname char(20) not null,
	spno char(8) ,
	ctno tinyint,
	lecture tinyint,
	experiment tinyint,
	semester tinyint,
	credit tinyint,
	foreign key(spno) references speciality(spno),
	primary key(cno)

);

create table teacher_course (
	tcid smallint,
	t_no char(8),
	spno char(8),
	class_no char(4),
	cno char(10) not null,
	semester char(6),
	schoolyear char(10),
	foreign key (t_no) references teacher(t_no),
	foreign key (spno) references speciality(spno),
	foreign key(cno) references course(cno),
	primary key(tcid)
);


