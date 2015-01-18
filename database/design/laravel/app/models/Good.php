<?php

class Good extends Eloquent {
    protected $table = 'good';
    protected $primaryKey = array('user_id', 'answer_id');
    public $timestamps = false;
}
