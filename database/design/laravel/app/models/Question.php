<?php

class Question extends Eloquent {
    protected $table = 'question';
    protected $primaryKey = 'id';

    public function asker() {
        return $this->belongsTo('User', 'ask_user_id');
    }

    public function answers() {
        return $this->hasMany('Answer', 'id');
    }

    public function add_answers() {

    }
}
