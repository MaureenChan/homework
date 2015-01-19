<?php

class UserTableSeeder extends Seeder {
    public function run() {
        $faker = Faker\Factory::create();
        $faker->seed(1234);

        for ($i = 0; $i < 100; $i++) {
            $user = DB::table('user')->insert(array(
                'name' => $faker->userName,
                'password' => $faker->password,
            ));
        }
    }
}
