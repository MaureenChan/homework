<?php
class Comment extends Eloquent {
    protected $table = 'comment';
    public $timestamps = false;

    public function commenter() {
        return $this->belongsTo('User', 'user_id');
    }
}
