use SC;
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


insert into teacher(t_no, t_name, t_sex, t_birthday, dno, tech_title)
	values('9876', 'diaochan', 'wm', '1977-1-1', '1', 'laoshi');
insert into teacher(t_no, t_name, t_sex, t_birthday, dno, tech_title)
	values('9764', 'sunshang', 'wm', '1967-3-4', '2', 'jiaoshou');
insert into teacher(t_no, t_name, t_sex, t_birthday, dno, tech_title)
	values('9574', 'huang', 'mn', '1956-2-3', '3', 'fudaoyuan');
insert into teacher(t_no, t_name, t_sex, t_birthday, dno, tech_title)
	values('9367', 'sunquan', 'mn', '1967-4-3', '4', 'jiaoshou');
insert into teacher(t_no, t_name, t_sex, t_birthday, dno, tech_title)
	values('9463', 'dongzhuo', 'mn', '1969-6-4', '5', 'fujiaoshou');

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

insert into course(cno, cname, spno, ctno, lecture, experiment, semester, credit)
	values('123456', 'database', '100', '01', '5','6','2', '3');
insert into course(cno, cname, spno, ctno, lecture, experiment, semester, credit)
	values('234567', 'design', '105', '02', '5','2', '3', '3');
insert into course(cno, cname, spno, ctno, lecture, experiment, semester, credit)
	values('345678', 'games', '102', '02', '5','3', '2', '4');
insert into course(cno, cname, spno, ctno, lecture, experiment, semester, credit)
	values('456789', 'code', '103', '01', '7', '3', '2', '5');
insert into course(cno, cname, spno, ctno, lecture, experiment, semester, credit)
	values('567890', 'chess', '104', '02', '5', '2', '2', '1');
insert into course(cno, cname, spno, ctno, lecture, experiment, semester, credit)
	values('678901', 'card', '105', '01', '1', '4', '3', '2');
insert into course(cno, cname, spno, ctno, lecture, experiment, semester, credit)
	values('789012', 'dance', '100', '02', '2', '1', '3', '1');

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
