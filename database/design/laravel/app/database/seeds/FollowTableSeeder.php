<?php

class FollowTableSeeder extends Seeder {
    public function run() {
        $faker = Faker\Factory::create();
        $faker->seed(1234);

        for ($i = 0; $i < 50; $i++) {
            $follower = DB::table('follow')->insert(array(
                'user_id' => $faker->numberBetween($min = 1, $max = 100),
                'follower' => $faker->numberBetween($min = 1, $max = 100),
            ));
        }
        
    }
}
