<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateView extends Migration {

	/**
	 * Run the migrations.
	 *
	 * @return void
	 */
	public function up()
	{
        DB::statement('create view v_question as
            select question_id, ask_user_id, answer_id, answer_user_id 
                from question');

        DB::statement('create view v_comment as
            select id, user_id, answer_id
                from comment
            ');

	}

	/**
	 * Reverse the migrations.
	 *
	 * @return void
	 */
	public function down()
	{
		//
        DB::statement('drop view v_question');
        DB::statement('drop view v_comment');
	}

}
