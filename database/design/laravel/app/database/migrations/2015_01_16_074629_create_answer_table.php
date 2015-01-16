<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateAnswerTable extends Migration {

	/**
	 * Run the migrations.
	 *
	 * @return void
	 */
	public function up()
	{
		//
        Schema::create('answer', function($table) {
            $table->increments('answer_id');
            $table->string('answer', 1000)->nullable(false);
            $table->string('status', 20)->nullable(false);
            $table->integer('user_id')->unsigned();
            $table->datetime('answer_date');

            $table->foreign('user_id')
                ->references('user_id')->on('user')
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
        Schema::dropIfExists('answer');
	}

}
