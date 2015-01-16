<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateCommentTable extends Migration {

	/**
	 * Run the migrations.
	 *
	 * @return void
	 */
	public function up()
	{
		//
        Schema::create('comment', function($table) {
            $table->increments('id');
            $table->integer('user_id')->unsigned();
            $table->integer('answer_id')->unsigned();
            $table->integer('comment_id')->nullable(true);
            $table->string('comment', 1000)->nullable(false);
            $table->datetime('comment_date');

            $table->foreign('user_id')
                ->references('user_id')->on('user')
                ->onDelete('cascade');

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
        Schema::dropIfExists('comment');
	}

}
