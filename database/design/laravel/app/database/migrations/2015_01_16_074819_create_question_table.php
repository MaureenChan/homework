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
            $table->integer('ask_user_id')->unsigned();
            $table->integer('answer_id')->unsigned()->nullable(true);
            $table->integer('answer_user_id')->unsigned();
            $table->datetime('question_date');
            $table->index('question');
            $table->index('ask_user_id');
            $table->index('answer_id');
            $table->index('answer_user_id');

            $table->foreign('ask_user_id')
                ->references('user_id')->on('user');
            $table->foreign('answer_user_id')
                ->references('user_id')->on('user');

            $table->foreign('answer_id')
                ->references('answer_id')->on('answer')
                ->onDelete('cascade');
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
