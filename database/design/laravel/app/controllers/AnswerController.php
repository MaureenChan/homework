<?php

class AnswerController extends BaseController {
    public function update_answer() {
        $question_id = Input::get('question_id');
        $question = Question::find($question_id);
        if ($question == null) {
            return -1;
        } else {
            $answer = $question->answer;
            $answer->answer = Input::get('answer');
            $answer->save();
        }
        return Redirect::route('question', $question_id);
    }
}

