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
            $table->string('password', 100)->nullable(false);
            $table->string('gender', 10)->nullable(false);
            $table->datetime('birthday');
            $table->string('remember_token', 100)->nullable(true);
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
