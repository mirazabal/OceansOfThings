import {Injectable} from '@angular/core';

@Injectable()
export class UserService {
	private _name: string;
	private _age: number;

	constructor() {
		this._name = 'Jan CValjoan';
		this._age = 32;
	}

	get name() {
		return this._name;
	}

	set name(newName){
		this._name = newName;
	}


	get age(){
		return this._age;
	}
	set age(newAge){
		this._age = newAge;
	}

}



