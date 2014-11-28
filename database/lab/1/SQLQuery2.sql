use SC;
create table speciality1 (
	spno char(8)unique,
	dno char(6)  not null,
	spname char(20) not null,
	foreign key (dno) references department(dno),
	primary key(spno)
);