<?php

class AnswerTableSeeder extends Seeder {
    public function run() {
        $faker = Faker\Factory::create();
        $faker->seed(1234);

        for ($i = 0; $i < 50; $i++) {
            $answer = DB::table('answer')->insert(array(
                'answer' => $faker->sentence($nbWords = 10),
                'status' => $faker->numberBetween($min = 0, $max = 1),
                'user_id' => $faker->numberBetween($min = 1, $max = 100),
                'answer_date' => $faker->dateTime()->format('Y-m-d H:i:s')
            ));
        }
        
    }
}
