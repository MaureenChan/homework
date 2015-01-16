<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateLikeTable extends Migration {

	/**
	 * Run the migrations.
	 *
	 * @return void
	 */
	public function up()
	{
		//
        Schema::create('good', function($table) {
            $table->integer('user_id')->unsigned();
            $table->integer('answer_id')->unsigned();

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
        Schema::dropIfExists('good');
	}

}
