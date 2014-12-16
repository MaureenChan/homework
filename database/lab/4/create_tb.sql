use student;

create table department (
	dno char(8),
	dept_name char(20) not null,
	header char(8),
	primary key(dno)
);

create table speciality (
	spno char(8),
	dno char(8)  not null,
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

create table profession(
	pro_id char(8),
	pro_name char(20),
	primary key (pro_id)
);

create table student (
	s_no char(8),
	sname char(8) not null,
	sex char(2),
	sbirthday datetime,
	dno char(8) ,
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
	dno char(8),
	pro_id char(8),
	foreign key(dno) references department(dno),
	foreign key(pro_id) references profession(pro_id),
	primary key(t_no)
);

create table coursetype(
	type_id char(8),
	type_name char(20) not null,
	primary key (type_id)
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
	type_id char(8),
	ctno tinyint,
	lecture tinyint,
	experiment tinyint,
	semester tinyint,
	credit tinyint,
	foreign key(spno) references speciality(spno),
	foreign key(type_id) references coursetype(type_id),
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

create table punishment_levels(
	punish_id char(8) not null,
	punish_name char(20) not null,
	punish_level char(8),
	dno char(8) ,
	spno char(8),
	foreign key (dno) references department(dno),
	foreign key (spno) references speciality(spno),
	primary key(punish_id)
);

create table punishment(
	record_id char(8) not null,
	punish_id char(8),
	s_no char(8),
	punish_date datetime,
	foreign key (s_no) references student(s_no),
	foreign key (punish_id) references punishment_levels(punish_id),
	primary key (record_id)
);

create table reward_levels(
	reward_id char(8) not null,
	reward_name char(20) not null,
	reward_level char(8),
	dno char(8),
	spno char(8),
	foreign key (dno) references department(dno),
	foreign key (spno) references speciality(spno),
	primary key(reward_id)
);

create table reward(
	record_re_id char(8) not null,
	reward_id char(8),
	s_no char(8),
	reward_date datetime,
	foreign key (s_no) references student(s_no),
	foreign key (reward_id) references reward_levels(reward_id),
	primary key (record_re_id)
);

create table chengs_code(
	change_id char(8),
	change_name char(20) not null, 
	dno char(8),
	spno char(8),
	foreign key (dno) references department(dno),
	foreign key (spno) references speciality(spno),
	primary key(change_id)
);

create table cheng(
	record_ch_id char(8) not null,
	change_id char(8),
	s_no char(8),
	change_date datetime,
	foreign key (s_no) references student(s_no),
	foreign key (change_id) references chengs_code(change_id),
	primary key (record_ch_id)
);
