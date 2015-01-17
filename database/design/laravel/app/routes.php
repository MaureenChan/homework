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
Route::get('/user/login', array(
    'as' => 'login',
    'uses' => 'UserController@get_login'
));

Route::get('/users/all', array(
    'as' => 'users',
    'uses' => 'UserController@all_user'
));

Route::get('/user/{user_id}', array(
    'as' => 'user',
    'uses' => 'UserController@get_by_id'
));

Route::get('/user/{user_id}/questions', array(
    'as' => 'question',
    'uses' => 'UserController@get_questions'
));

Route::get('/user/follow/{user_id}', array(
    'as' => 'follow',
    'uses' => 'UserController@add_follower'
));

Route::post('question/add_answer', array(
    'as' => 'add_answer',
    'uses' => 'QuestionController@add_answer'
));

