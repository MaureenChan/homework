<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateUserTable extends Migration {

	/**
	 * Run the migrations.
	 *
	 * @return void
	 */
	public function up()
	{
        Schema::create('user', function($table) {
            $table->increments('user_id');
            $table->string('name', 20)->nullable(false);
            $table->string('password', 16)->nullable(false);
            $table->string('gender', 10)->nullable(false);
            $table->datetime('birthday');
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
	}

}
