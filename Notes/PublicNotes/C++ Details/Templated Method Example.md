
Given a situation where you have a vector of a base class, we'll use Items for this example.

```c++
std::vector<Item*> m_Items;
```

We need a method to find an Item of a given subclass. For example, let's say you want to search the Items list for the first potion.

```c++
Item* Inventory::FindFirstItemOfType(std::string type)
{
	for( Item* pItem : m_Items )
	{
		if( pItem->GetType() == type )
		{
			return pItem;
		}
	}

	return nullptr;
}
```

This works, but calling code will likely need to cast the result to the correct type, for instance:

```c++
Item* pItem = m_Inv.FindFirstItemOfType( "Sword" );

if( pItem )
{
	Sword* pSword = static_cast<Sword>( pItem );
}
```

This could be done better with a templated function that would handle the cast for you internally

```c++
template <class ItemType>
ItemType* Inventory::FindFirstItemOfType()
{
	for( Item* pItem : m_Items )
	{
		if( pItem->GetType() == ItemType::GetStaticType() )
		{
			return static_cast<ItemType*>( pItem );
		}
	}

	return nullptr;
}
```

Then calling the method is a bit cleaner from the callers perspective:

```c++
Sword* pSword = m_Inv.FindFirstItemOfType<Sword>();
```
