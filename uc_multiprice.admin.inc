<?php

/**
 *  Function to generate the form
 */
function uc_multiprice_admin_roles() {
  if (!user_access('administer multiprice roles')) {
    return FALSE;
  }

  $form = array();

  $form['uc_multiprice_admin_roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Multiprice enabled roles'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Please select the roles for which you want to set multiprices. The roles are shown ordered by weight.')
  );

  $user_roles = user_roles();
  $form['uc_multiprice_admin_roles']['uc_multiprice_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#default_value' => variable_get('uc_multiprice_roles', array()),
    '#options' => $user_roles,
  );
  $form['uc_multiprice_admin_roles_fallback'] = array(
    '#type' => 'fieldset',
    '#title' => t('Multiprice roles fallback'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Please configure the fallback procedure for role based pricing. If there is no role based price available should the module fall back to country based pricing (if available) or to the default product price? Probably best to enable this setting when you have set country prices in different currencies than the store default currency.')
  );
  $form['uc_multiprice_admin_roles_fallback']['uc_multiprice_roles_fallback'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fall back to default product price'),
    '#default_value' => variable_get('uc_multiprice_roles_fallback', NULL),
  );

  return system_settings_form($form);
}

/**
 *  Function to generate the form
 */
function uc_multiprice_admin_currencies() {
  if (!user_access('administer multiprice')) {
    return FALSE;
  }

  $form = array();

  $form['uc_multiprice_admin_currencies'] = array(
    '#type' => 'fieldset',
    '#title' => t('Disable unpriced product'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Disable the quantity field and add to cart button for products that do not have a multiprice set when the <a href="@pricehandler">Multiprice Currency Handler</a> is enabled and the users country currency differs from the default currency. This prevents a product falling back to the default amount but using the incorrect currency for it.', array('@pricehandler' => url('admin/store/settings/price-handlers')))
  );
  $form['uc_multiprice_admin_currencies']['uc_multiprice_currency_disable_unpriced_product'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => variable_get('uc_multiprice_currency_disable_unpriced_product', NULL),
  );

  return system_settings_form($form);
}

/**
 * Implementation of hook_help().
 */
function uc_multiprice_help($path, $arg) {
  global $user;

  switch ($path) {
    case 'admin/store/settings/multiprice':
      return t('<p>The <a href="@pricehandler">Multicurrency Currency Handler</a> allows you to use the currency set for a country in the <a href="@countryformats">country formats</a> with the displayed price. When this <a href="@pricehandler">handler</a> is enabled it is expected that pricing has been set for each product for each enabled country.</p>
               <p><strong>Example</strong><br />
                Your Ubercart store has USA as the default country. There are currently two products in the store; a laptop and a desktop computer. For the laptop the default sell price amount has been set at 1000, for buyers from India the sell price amount has been set at 35000. With the <a href="@pricehandler">Multicurrency Currency Handler</a> enabled and the
                correct <a href="@countryformats">country formats</a> set the Ubercart store will show a sell price of $1,000.00 to USA buyers and a price of Rs. 35,000.00 to Indian buyers.</p>
                <p>For the desktop the default sell price amount has been set to 500, but the admin has omitted the set a price for buyers from India. The Ubercart store will show a sell price of $500.00 to USA buyers, but the <strong>incorrect price</strong> of Rs. 500.00 to Indian buyers (which is less than $10).</p>
                <p>Ofcourse this will dramatically increase sales to India but the stores profits will plumit. To prevent this the admin should always set a price per product per country if <a href="@pricehandler">Multicurrency Currency Handler</a> is enabled. By enabling the checkbox below the module will disable the quantity field
                and the add to cart button for products which do not have a multiprice for the buyers country in case the admin omits to set a price per country for a product. Thereby preventing products being sold at the wrong sell price.</p>
               ', array(
        '@pricehandler' => url('admin/store/settings/price-handlers'),
        '@countryformats' => url('admin/store/settings/countries/edit/formats')
      ));
  }
}
