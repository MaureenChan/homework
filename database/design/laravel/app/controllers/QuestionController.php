<?php

class QuestionController extends BaseController {
    public function get_answers($id) {
        $question = Question::find($id);
        $answers = $question->answers;
        return Response::json($answers);
    }

    public function add_answer() {

    }
}

