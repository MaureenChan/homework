<?php

class QuestionTableSeeder extends Seeder {
    public function run() {
        $faker = Faker\Factory::create();
        $faker->seed(1234);

        for ($i = 0; $i < 50; $i++) {
            $question = DB::table('question')->insert(array(
                'question' => $faker->sentence($nbWords = 10),
                'question_detail' => $faker->sentence($nbWords = 10),
                'ask_user_id' => $faker->numberBetween($min = 1, $max = 100),
                'answer_id' => $faker->numberBetween($min = 1, $max = 50),
                'question_date' => $faker->dateTime()->format('Y-m-d H:i:s')
            ));
        }
        
    }
}
