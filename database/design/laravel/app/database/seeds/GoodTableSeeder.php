<?php

class GoodTableSeeder extends Seeder {
    public function run() {
        $faker = Faker\Factory::create();
        $faker->seed(1234);

        for ($i = 0; $i < 100; $i++) {
            $good = DB::table('good')->insert(array(
                'user_id' => $faker->numberBetween($min = 1, $max = 100),
                'answer_id' => $faker->numberBetween($min = 1, $max = 100),
            ));
        }
        
    }
}
