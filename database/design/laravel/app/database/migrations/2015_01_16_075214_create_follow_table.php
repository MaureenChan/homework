<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateFollowTable extends Migration {

	/**
	 * Run the migrations.
	 *
	 * @return void
	 */
	public function up()
	{
		//
        Schema::create('follow', function($table) {
            $table->integer('user_id')->unsigned();
            $table->integer('follower')->unsigned();

            $table->primary(array('user_id', 'follower'));
            $table->foreign('user_id')
                ->references('user_id')->on('user')
                ->onDelete('cascade');

            $table->foreign('follower')
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
        Schema::dropIfExists('follow');
	}

}
