<?php

use Illuminate\Auth\UserTrait;
use Illuminate\Auth\UserInterface;
use Illuminate\Auth\Reminders\RemindableTrait;
use Illuminate\Auth\Reminders\RemindableInterface;

class User extends Eloquent implements UserInterface, RemindableInterface {

	use UserTrait, RemindableTrait;

	/**
	 * The database table used by the model.
	 *
	 * @var string
	 */
	protected $table = 'user';

	/**
	 * The attributes excluded from the model's JSON form.
	 *
	 * @var array
	 */
	protected $hidden = array('password', 'remember_token');

    protected $primaryKey = 'user_id';

    public $timestamps = false;
    
    public function questions() {
        return $this->hasMany('Question', 'ask_user_id');
    }

    public function is_my_follower($id) {
        $count = Follow::where('user_id', '=', $this->user_id)
            ->where('follower', '=', $id)
            ->count();
        if ($count)
            return true;
        else
            return false;
    }
}
