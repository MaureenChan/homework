<?php

class DatabaseSeeder extends Seeder {

	/**
	 * Run the database seeds.
	 *
	 * @return void
	 */
	public function run()
	{
		Eloquent::unguard();

        $this->call('UserTableSeeder');
        $this->call('AnswerTableSeeder');
        $this->call('QuestionTableSeeder');
        $this->call('CommentTableSeeder');
        $this->call('FollowTableSeeder');
        $this->call('GoodTableSeeder');


	}

}
