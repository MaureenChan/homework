<?php

class AnswerTableSeeder extends Seeder {
    public function run() {
        $faker = Faker\Factory::create();
        $faker->seed(1234);

        for ($i = 0; $i < 100; $i++) {
            $answer = DB::table('answer')->insert(array(
                'answer' => $faker->sentence($nbWords = 100),
                'answer_date' => $faker->dateTime()->format('Y-m-d H:i:s')
            ));
        }
        
    }
}
