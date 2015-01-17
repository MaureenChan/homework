<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateQuestionTable extends Migration {

	/**
	 * Run the migrations.
	 *
	 * @return void
	 */
	public function up()
	{
		//
        Schema::create('question', function($table) {
            $table->increments('question_id');
            $table->string('question',1000)->nullable(false);
            $table->string('question_detail', 1000)->nullable(true);
            $table->integer('ask_user_id')->unsigned();
            $table->integer('answer_id')->unsigned()->nullable(true);
            $table->integer('answer_user_id')->unsigned();
            $table->datetime('question_date');

            $table->foreign('ask_user_id')
                ->references('user_id')->on('user')
                ->onDelete('cascade');
            $table->foreign('answer_user_id')
                ->references('user_id')->on('user')
                ->onDelete('cascade');

            $table->foreign('answer_id')
                ->references('answer_id')->on('answer');
        });
	}

	/**
	 * Reverse the migrations.
	 *
	 * @return void
	 */
	public function down()
	{
		//
        Schema::dropIfExists('question');
	}

}
