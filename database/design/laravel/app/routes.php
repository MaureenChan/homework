<?php

/*
|--------------------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| Here is where you can register all of the routes for an application.
| It's a breeze. Simply tell Laravel the URIs it should respond to
| and give it the Closure to execute when that URI is requested.
|
*/

Route::get('/', array(
    'as' => 'home',
    'uses' => 'HomeController@index'
));

// login stuff
Route::get('/user/register', array(
    'as' => 'register',
    'uses' => 'UserController@get_register'
));
Route::post('/user/post_register', array(
    'as' => 'post_register',
    'uses' => 'UserController@post_register'
));
Route::get('/user/login', array(
    'as' => 'login',
    'uses' => 'UserController@get_login'
));
Route::get('/user/logout', array(
    'as' => 'logout',
    'uses' => 'UserController@get_logout'
));
Route::post('/user/post_login', array(
    'as' => 'post_login',
    'uses' => 'UserController@post_login'
));

Route::get('/me', array(
    'as' => 'me',
    'uses' => 'UserController@me'
));

// get all users
Route::get('/users/all', array(
    'as' => 'users',
    'uses' => 'UserController@all_user'
));

// get all my follower
Route::get('/user/my_follower', array(
    'as' => 'followers',
    'uses' => 'UserController@my_follower'
));

// get all my following
Route::get('/user/my_following', array(
    'as' => 'followings',
    'uses' => 'UserController@my_following'
));

// add follower
Route::get('/user/follow/{user_id}', array(
    'as' => 'follow',
    'uses' => 'UserController@follow'
));

// delete follower
Route::get('/user/unfollow/{user_id}', array(
    'as' => 'unfollow',
    'uses' => 'UserController@unfollow'
));

// get user by id
Route::get('/user/{user_id}', array(
    'as' => 'user',
    'uses' => 'UserController@get_by_id'
));

// get my question
Route::get('/user/{user_id}/questions', array(
    'as' => 'question',
    'uses' => 'UserController@get_questions'
));


Route::post('/ask', array(
    'as' => 'ask',
    'uses' => 'UserController@ask'
));

Route::filter('auth', function () {
    if (!Auth::check()) {
        return Redirect::route('login');
    }
});
