<?php

class Good extends Eloquent {
    protected $table = 'good';
    public $timestamps = false;

    public function answer() {
        return $this->belongsTo('Answer', 'answer_id', 'answer_id');
    }
}
