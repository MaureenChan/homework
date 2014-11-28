use northwind;
select * from products;

select * from products
	where UnitPrice < 20;

select Max(UnitPrice) as highest_price from products;

select distinct products.ProductID, ProductName from products, [Order Details]
		where products.ProductID = [Order Details].ProductID ;

select ProductID, ProductName from products
	where ProductID in (
		select ProductID from [Order Details]
			where OrderID in (
				select OrderID from Orders
					where CustomerID = 'AROUT'
			)
	);

select ProductID, ProductName from products
	where UnitPrice > '20' 
		and ProductID in (
			select ProductID from [Order Details]
				where OrderID in (
					select OrderID from Orders
						where CustomerID = 'AROUT'
				)
		);
	

select * from products
	where UnitPrice in (
		select Max(UnitPrice) from products
	);
