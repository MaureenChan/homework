<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class Init extends Migration {

	/**
	 * Run the migrations.
	 *
	 * @return void
	 */
	public function up()
	{
        Schema::create('user', function($table) {
            $table->increments('id');
            $table->string('name', 10)->nullable(false);
            $table->string('password', 16)->nullable(false);
            $table->string('gender', 10)->nullable(false);
            $table->datetime('birthday');
        });

        Schema::create('answer', function($table) {
            $table->increments('id');
            $table->string('answer', 1000)->nullable(false);
            $table->string('status', 20)->nullable(false);
            $table->integer('user_id')->unsigned();
            $table->datetime('answer_date');

            $table->foreign('user_id')
                ->references('id')->on('user')
                ->onDelete('cascade');
        });

        Schema::create('question', function($table) {
            $table->increments('id');
            $table->string('question',1000)->nullable(false);
            $table->string('question_detail', 1000)->nullable(true);
            $table->integer('ask_user_id')->unsigned();
            $table->integer('answer_id')->unsigned();
            $table->datetime('question_date');

            $table->foreign('ask_user_id')
                ->references('id')->on('user')
                ->onDelete('cascade');

            $table->foreign('answer_id')
                ->references('id')->on('answer')
                ->onDelete('cascade');
        });

        Schema::create('comment', function($table) {
            $table->increments('id');
            $table->integer('user_id')->unsigned();
            $table->integer('answer_id')->unsigned();
            $table->integer('comment_id')->nullable(true);
            $table->string('comment', 1000)->nullable(false);
            $table->datetime('comment_date');

            $table->foreign('user_id')
                ->references('id')->on('user')
                ->onDelete('cascade');

            $table->foreign('answer_id')
                ->references('id')->on('answer')
                ->onDelete('cascade');
        });

        Schema::create('follow', function($table) {
            $table->integer('user_id')->unsigned();
            $table->integer('follower')->unsigned();

            $table->foreign('user_id')
                ->references('id')->on('user')
                ->onDelete('cascade');

            $table->foreign('follower')
                ->references('id')->on('user')
                ->onDelete('cascade');
        });

        Schema::create('like', function($table) {
            $table->integer('user_id')->unsigned();
            $table->integer('answer_id')->unsigned();

            $table->foreign('user_id')
                ->references('id')->on('user')
                ->onDelete('cascade');

            $table->foreign('answer_id')
                ->references('id')->on('answer')
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
        Schema::dropIfExists('user');
        Schema::dropIfExists('question');
        Schema::dropIfExists('answer');
        Schema::dropIfExists('comment');
        Schema::dropIfExists('follow');
        Schema::dropIfExists('like');
	}

}
