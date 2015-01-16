
<?php

class CommentTableSeeder extends Seeder {
    public function run() {
        $faker = Faker\Factory::create();
        $faker->seed(1234);

        for ($i = 0; $i < 50; $i++) {
            $comment = DB::table('comment')->insert(array(
                'comment' => $faker->sentence($nbWords = 10),
                'user_id' => $faker->numberBetween($min = 1, $max = 100),
                'answer_id' => $faker->numberBetween($min = 1, $max = 50),
                'comment_date' => $faker->dateTime()->format('Y-m-d H:i:s')
            ));
        }
        
    }
}
