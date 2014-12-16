use student;
insert into department(dno, dept_name, header)
	values('1', 'computer', 'Mr.chen');
insert into department(dno, dept_name, header)
	values('2', 'math', 'Mr.lin');
insert into department(dno, dept_name, header)
	values('3', 'chemistry', 'Mr.chen');
insert into department(dno, dept_name, header)
	values('4', 'physic', 'Mr.feng');
insert into department(dno, dept_name, header)
	values('5', 'art', 'Mr.liu');


insert into speciality(spno, dno, spname)
	values('100', '1', 'CS');
insert into speciality(spno, dno, spname)
	values('101', '2', 'MA');
insert into speciality(spno, dno, spname)
	values('102', '1', 'SW');
insert into speciality(spno, dno, spname)
	values('103', '3', 'MD');
insert into speciality(spno, dno, spname)
	values('104', '4', 'LED');
insert into speciality(spno, dno, spname)
	values('105', '5', 'DS');


insert into class(spno, class_no, header)
	values('100', '001', 'Mr.Wu');
insert into class(spno, class_no, header)
	values('101', '006', 'Mr.Ao');
insert into class(spno, class_no, header)
	values('102', '009', 'Mr.Du');
insert into class(spno, class_no, header)
	values('103', '002', 'Mr.Yang');
insert into class(spno, class_no, header)
	values('104', '003', 'Mr.Wang');
insert into class(spno, class_no, header)
	values('105', '005', 'Mr.Lao');


insert into student(s_no, sname, sex, sbirthday, dno, spno, class_no)
	values('3213', '³Âç²Ãç', 'mn', '1993-2-4', '1', '100', '001');
insert into student(s_no, sname, sex, sbirthday, dno, spno, class_no)
	values('3218', 'lisi', 'wm', '1994-6-4', '2', '101', '006');
insert into student(s_no, sname, sex, sbirthday, dno, spno, class_no)
	values('3220', 'sunwu', 'mn', '1995-6-3', '3', '103', '002');
insert into student(s_no, sname, sex, sbirthday, dno, spno, class_no)
	values('3222', 'liuyi', 'wm', '1992-6-7', '4', '104', '003');
insert into student(s_no, sname, sex, sbirthday, dno, spno, class_no)
	values('3123', 'tangwei', 'wm', '1993-6-3', '5', '105', '005');
insert into student(s_no, sname, sex, sbirthday, dno, spno, class_no)
	values('3133', 'wuyanzu', 'mn', '1994-7-3', '1', '102', '009');

insert into profession(pro_id, pro_name)
	values('0012', 'laoshi');
insert into profession(pro_id, pro_name)
	values('0013', 'jiaoshou');
insert into profession(pro_id, pro_name)
	values('0014', 'fudaoyuan');

insert into teacher(t_no, t_name, t_sex, t_birthday, dno, pro_id)
	values('9876', 'diaochan', 'wm', '1977-1-1', '1', '0012');
insert into teacher(t_no, t_name, t_sex, t_birthday, dno, pro_id)
	values('9764', 'sunshang', 'wm', '1967-3-4', '2', '0013');
insert into teacher(t_no, t_name, t_sex, t_birthday, dno, pro_id)
	values('9574', 'huang', 'mn', '1956-2-3', '3', '0014');
insert into teacher(t_no, t_name, t_sex, t_birthday, dno, pro_id)
	values('9367', 'sunquan', 'mn', '1967-4-3', '4', '0012');
insert into teacher(t_no, t_name, t_sex, t_birthday, dno, pro_id)
	values('9463', 'dongzhuo', 'mn', '1969-6-4', '5', '0014');

insert into coursetype(type_id, type_name)
	values('a', 'zhuanye');
insert into coursetype(type_id, type_name)
	values('b', 'renwen');
insert into coursetype(type_id, type_name)
	values('c', 'jichu');
insert into coursetype(type_id, type_name)
	values('d', 'xuanxiu');

insert into student_course(s_no, tcid, score)
	values('3213', '3333', '90');
insert into student_course(s_no, tcid, score)
	values('3220', '4444', '89');
insert into student_course(s_no, tcid, score)
	values('3218', '6666', '78');
insert into student_course(s_no, tcid, score)
	values('3133', '9999', '79');
insert into student_course(s_no, tcid, score)
	values('3123', '2222', '98');
insert into student_course(s_no, tcid, score)
	values('3133', '5555', '87');
insert into student_course(s_no, tcid, score)
	values('3222', '2222', '67');

insert into course(cno, cname, spno, type_id, ctno, lecture, experiment, semester, credit)
	values('123456', 'database', '100', 'a', '01', '5','6','2', '3');
insert into course(cno, cname, spno, type_id, ctno, lecture, experiment, semester, credit)
	values('234567', 'design', '105', 'a', '02', '5','2', '3', '3');
insert into course(cno, cname, spno, type_id, ctno, lecture, experiment, semester, credit)
	values('345678', 'games', '102', 'b', '02', '5','3', '2', '4');
insert into course(cno, cname, spno, type_id, ctno, lecture, experiment, semester, credit)
	values('456789', 'code', '103', 'b','01', '7', '3', '2', '5');
insert into course(cno, cname, spno, type_id, ctno, lecture, experiment, semester, credit)
	values('567890', 'chess', '104', 'c', '02', '5', '2', '2', '1');
insert into course(cno, cname, spno, type_id, ctno, lecture, experiment, semester, credit)
	values('678901', 'card', '105','c', '01', '1', '4', '3', '2');
insert into course(cno, cname, spno, type_id, ctno, lecture, experiment, semester, credit)
	values('789012', 'dance', '100','b', '02', '2', '1', '3', '1');

insert into teacher_course(tcid, t_no, spno, class_no, cno, semester, schoolyear)
	values('2222', '9876', '100','001', '345678','2', '2014');
insert into teacher_course(tcid, t_no, spno, class_no, cno, semester, schoolyear)
	values('9999', '9367', '102', '002', '678901', '3', '2011' );
insert into teacher_course(tcid, t_no, spno, class_no, cno, semester, schoolyear)
	values('6666', '9367', '103', '002', '789012', '3', '2013');
insert into teacher_course(tcid, t_no, spno, class_no, cno, semester, schoolyear)
	values('3333', '9764', '104', '003', '567890', '2', '2014');
insert into teacher_course(tcid, t_no, spno, class_no, cno, semester, schoolyear)
	values('5555', '9463', '101', '001', '234567','3', '2012');

insert into punishment_levels(punish_id, punish_name, punish_level, dno, spno)
	values('aa', 'chaoxi', '5', '1', '100');
insert into punishment_levels(punish_id, punish_name, punish_level, dno, spno)
	values('bb', 'zuobi', '8', '2', '101');
insert into punishment_levels(punish_id, punish_name, punish_level, dno, spno)
	values('cc', 'dajia', '9', '5', '105');


insert into punishment(record_id, punish_id, s_no, punish_date)
	values('88', 'aa', '3218', '2014-02-05');
insert into punishment(record_id, punish_id, s_no, punish_date)
	values('99', 'bb', '3220', '2013-05-06');
insert into punishment(record_id, punish_id, s_no, punish_date)
	values('77', 'cc', '3222', '2012-06-22');

insert into reward_levels(reward_id, reward_name, reward_level, dno, spno)
	values('333', 'quangguo', '1', '5', '105');
insert into reward_levels(reward_id, reward_name, reward_level, dno, spno)
	values('444', 'quansheng', '5', '3','103');
insert into reward_levels(reward_id, reward_name, reward_level, dno, spno)
	values('555', 'quanshijie', '9', '1', '100');

insert into reward(record_re_id, reward_id, s_no, reward_date)
	values('34', '333', '3220', '2014-03-22');

insert into chengs_code(change_id, change_name, dno, spno)
	values('084', 'zhuanye', '1', '101');

insert into cheng(record_ch_id, change_id, s_no, change_date)
	values('010', '084', '3218', '2011-3-11');
