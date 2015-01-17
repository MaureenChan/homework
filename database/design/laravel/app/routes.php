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

Route::get('/', function()
{
	return View::make('hello');
});

Route::get('/users/all', array(
    'as' => 'users',
    'uses' => 'UserController@all_user'
));

Route::get('/user/{user_id}', array(
    'as' => 'user',
    'uses' => 'UserController@get_by_id'
));

Route::get('user/{user_id}/questions', array(
    'as' => 'question',
    'uses' => 'UserController@get_questions'
));

Route::get('question/{question_id}/answers', array(
    'as' => 'answer',
    'uses' => 'QuestionController@get_answers'
));

Route::post('question/add_answer', array(
    'as' => 'add_answer',
    'uses' => 'QuestionController@add_answer'
));


